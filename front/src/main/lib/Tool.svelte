<script>
    import { tool, changeTool
     } from "../tool";
</script>

<button onclick={changeTool} class="w-full flex p-2 gap-2 bg-neutral-900 text-2xl text-white text-center font-bold rounded-2xl shadow-2xl shadow-black">
    <div class="flex-1 py-2 rounded-2xl" class:bg-blue-800={$tool === 1}>
        Draw
    </div>
    <div class="flex-1 py-2 rounded-2xl" class:bg-blue-800={$tool === 0}>
        Erase
    </div>
</button>