<script>
    import { tool, changeTool
     } from "../tool";
</script>

<button onclick={changeTool} class="w-full border-10 border-neutral-900 rounded-b-2xl flex gap-2 text-2xl bg-neutral-900 text-white text-center font-bold">
    <div class="flex-1 py-2 rounded-2xl transition ease-initial duration-100" class:bg-blue-800={$tool === 1}>
        Draw
    </div>
    <div class="flex-1 py-2 rounded-2xl transition ease-initial duration-100" class:bg-blue-800={$tool === 0}>
        Erase
    </div>
</button>