<script lang="ts">
  import Display from './lib/Display.svelte';
    import Erase from './lib/Erase.svelte';
</script>

<main>
  <div class="flex justify-center items-center">
    <Display />
  </div>
  <div class="flex justify-center items-center gap-5 p-5 mr-3">
    <button on:click = {() => window.location.href = '/settings'} class="bg-lime-800 hover:bg-lime-900 active:bg-lime-950 rounded-3xl size-xl text-white px-5 py-3 text-3xl shadow-2xl font-bold shadow-neutral-900">Settings</button>
    <Erase />
  </div>

</main>